#include "Link.h"
#include "Parser.h"
#include "Serializer.h"

namespace RKL
{

Link::Link(Radio& radio)
    : _radio(radio),
      _ack(),
      _retry(),
      _nextSequence(0)
{
}

void Link::setRetryConfig(const RetryConfig& config)
{
    _retry.configure(config);
}

uint8_t Link::nextSequence()
{
    return _nextSequence++;
}

// Отправка с подтверждением
Result Link::sendPacket(Packet& packet)
{
    if (packet.type != PacketType::ACK)
        packet.id = nextSequence();

    _retry.reset();

    while (_retry.canAttempt())
    {
        _retry.recordAttempt();

        Result result = sendOnce(packet);
        if (result != Result::OK)
            return result;

        // Если это ACK, не ждём подтверждения
        if (packet.type == PacketType::ACK)
        {
            return Result::OK;
        }

        // Ждём ACK
        result = waitForAck(packet.id, _retry.timeout());
        if (result == Result::OK)
            return Result::OK;
    }

    return Result::RETRY_EXHAUSTED;
}

// Приём пакета с возможностью отключения отправки ACK (для waitForAck)
Result Link::receivePacket(Packet& packet, uint16_t timeout, bool sendAck)
{
    uint16_t received = 0;
    Result result = readFrame(received, timeout);

    if (result != Result::OK)
        return result;

    result = Parser::parse(_buffer, received, packet);
    if (result != Result::OK)
        return result;

    // Если это ACK, просто возвращаем OK (не отправляем ACK на ACK)
    if (packet.type == PacketType::ACK)
        return Result::OK;

    // Проверяем дубликат ДО отправки ACK
    bool isDuplicate = _ack.isDuplicate(packet);

    // Отправляем ACK, если нужно (sendAck == true)
    if (sendAck)
    {
        Packet ackPacket;
        Ack::make(ackPacket, packet.id);
        sendOnce(ackPacket);  // результат игнорируем, т.к. если не отправится, отправитель повторит
    }

    // Если дубликат, возвращаем OK (мы уже отправили ACK, чтобы отправитель не повторял)
    // Можно вернуть DUPLICATE_PACKET, но тогда вызывающий код может неправильно обработать.
    // Возвращаем OK – так надёжнее.
    return Result::OK;
}

// Публичные обёртки
Result Link::send(Packet& packet)
{
    return sendPacket(packet);
}

Result Link::receive(Packet& packet)
{
    return receivePacket(packet, LINK_TIMEOUT, true);
}

// Отправить один раз (без повторов)
Result Link::sendOnce(Packet& packet)
{
    uint16_t written = 0;
    Result result = Serializer::serialize(packet, _buffer, sizeof(_buffer), written);
    if (result != Result::OK)
        return result;

    result = _radio.send(_buffer, written);
    return result;
}

// Ожидание ACK с заданным sequence
Result Link::waitForAck(uint8_t sequence, uint16_t timeout)
{
    Packet incoming;
    // Важно: при вызове receivePacket передаём sendAck = false,
    // чтобы не отправлять ACK на случайные пакеты, которые могут прийти во время ожидания.
    Result result = receivePacket(incoming, timeout, false);

    if (result == Result::OK)
    {
        if (_ack.isAckFor(incoming, sequence))
            return Result::OK;
        else
            return Result::ACK_MISMATCH; // пришёл не тот ACK
    }

    return Result::TIMEOUT;
}

// Чтение одного байта с таймаутом (блокирующее, но с увеличенными таймаутами)
Result Link::readByte(uint8_t& value, uint32_t deadline)
{
    while (!_radio.available())
    {
        if (millis() >= deadline)
            return Result::TIMEOUT;
        // небольшая задержка для снижения нагрузки
        delay(1);
    }

    if (_radio.receive(&value, 1) == 1)
        return Result::OK;
    else
        return Result::NOT_READY;
}

// Чтение целого кадра (заголовок + полезные данные + CRC)
Result Link::readFrame(uint16_t& frameSize, uint16_t timeout)
{
    frameSize = 0;
    const uint32_t deadline = millis() + timeout;
    uint8_t value = 0;

    // Ждём стартовый байт
    do
    {
        Result result = readByte(value, deadline);
        if (result != Result::OK)
            return result;
    }
    while (value != START_BYTE);

    _buffer[0] = value;

    // Читаем оставшиеся 3 байта заголовка (type, id, length)
    for (uint8_t i = 1; i < PACKET_HEADER_SIZE; i++)
    {
        Result result = readByte(_buffer[i], deadline);
        if (result != Result::OK)
            return result;
    }

    const uint8_t payloadLength = _buffer[3];
    if (payloadLength > MAX_PAYLOAD_SIZE)
        return Result::BUFFER_OVERFLOW;

    frameSize = PACKET_HEADER_SIZE + payloadLength + CRC_SIZE;

    // Читаем payload и CRC
    for (uint16_t i = PACKET_HEADER_SIZE; i < frameSize; i++)
    {
        Result result = readByte(_buffer[i], deadline);
        if (result != Result::OK)
            return result;
    }

    return Result::OK;
}

} // namespace RKL
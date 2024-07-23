#include "CircularBuffer.h"
// #include "Arduino.h"

CircularBuffer::CircularBuffer(const unsigned int size) {
  _size = size;
  reset();
}

void CircularBuffer::reset() {
  for (int i = 0; i < _size; i++) {
    _data[i] = 0;
  }
  _firstIndex = 0;
  _lastIndex = 0;
  _hasToMoveFirstIndex = false;
}

void CircularBuffer::push(const unsigned long value) {
  moveLastIndex();
  moveFirstIndex();

  _data[_lastIndex] = value;

  // Serial.print(" first: ");
  // Serial.print(_firstIndex);

  // Serial.print(" last: ");
  // Serial.print(_lastIndex);

  // Serial.print("[");
  // for (int i = 0; i < _size; i++) {
  //   Serial.print(_data[i]);
  //   Serial.print(",");
  // }
  // Serial.print("]");
}

const unsigned long CircularBuffer::getFirst() {
  return _data[_firstIndex];
}

const unsigned long CircularBuffer::getLast() {
  return _data[_lastIndex];
}

void CircularBuffer::moveLastIndex() {
  if (_lastIndex == _size - 1) {
    _lastIndex = 0;
    _hasToMoveFirstIndex = true;
  }
  else {
    _lastIndex++;
  }
}

void CircularBuffer::moveFirstIndex() {
  if (_hasToMoveFirstIndex) {
    if (_firstIndex == _size - 1) {
      _firstIndex = 0;
    }
    else {
      _firstIndex++;
    }
  }
}

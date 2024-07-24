#ifndef CircularBuffer_h
#define CircularBuffer_h

class CircularBuffer {
public:
  CircularBuffer(const unsigned int size);
  void push(const unsigned long);
  void reset();
  const unsigned long getFirst();
  const unsigned long getLast();

private:
  unsigned int _size;
  unsigned long _data[100];
  unsigned int _firstIndex;
  unsigned int _lastIndex;
  bool _hasToMoveFirstIndex;

  void moveLastIndex();
  void moveFirstIndex();
};

#endif
#ifndef SUBJECT_H
#define SUBJECT_H
#include <string>
#include <vector>
class TextDisplay;
//class GraphicsDisplay;
class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  void notifyObservers(char t, int x, int y);
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif

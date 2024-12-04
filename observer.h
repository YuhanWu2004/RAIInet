#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Player;

class Observer {
 public:
  virtual void notify() = 0;
  virtual ~Observer() = default;
  virtual Player *getPlayer() const = 0;
};

#endif

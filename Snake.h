#ifndef SNAKE_H
#define SNAKE_H
#include <list>

class Snake
{
public:
	Snake();

	struct Cord
	{
		int x = 0;
		int y = 0;
	};

	void move(int deltaX, int deltaY);
	const Cord getHead() const;
	const std::list<Cord> getSnake() const;
	void reset();
	void grow();
	bool containsCord(Cord cord) const;
	bool headIntersectsBody() const;
private:
	Cord head;
	Cord previousEnd;
	std::list<Cord> body;

	
};
#endif



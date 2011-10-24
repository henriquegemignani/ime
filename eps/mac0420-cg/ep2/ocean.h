#ifndef OCEAN_H_
#define OCEAN_H_

class Ocean {
public:
	Ocean(int startx, int starty, int endx, int endy);
	~Ocean();
	void Render();
private:
	float originx, originy;
	int width, height;
};

#endif

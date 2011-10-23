#ifndef ISLAND_H_
#define ISLAND_H_

class Island {
public:
	Island(int startx, int starty, int endx, int endy, char *filename);
	~Island();
	void Render();
private:
	float originx, originy;
	int width, height;
	int **height_map;
};

#endif

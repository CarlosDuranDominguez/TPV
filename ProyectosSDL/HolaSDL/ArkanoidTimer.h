#include<ctime>

class ArkanoidTimer {
private:
	time_t* _firstTime;
public:
	ArkanoidTimer() { 
		_firstTime = new time_t();
		time(_firstTime); 
	}
	~ArkanoidTimer() { delete _firstTime; }
	double getSeconds() const { 
		time_t now;
		time(&now);
		return difftime(now, *_firstTime);
	}
	void delay(double time) {
		*_firstTime -= time;
	}
	void reset() {
		time(_firstTime);
	}
};
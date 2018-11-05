#include"Counter.h"
#include<math.h>
int Counter::setScore(const int num) { 
	text->setText(to_string(num));
	return score = num; 
}
int Counter::increaseScore(const int num) { 
	text->setText(to_string(score += num));
	return score ; 
};
void Counter::render() const{
	text->render();
}
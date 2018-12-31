#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"


std::string guesses;
std::string randomWord;
ros::Subscriber sub;
std::vector <std::string> words;
int counterWrong=0;
int counterRight=0;



void randomwords() {

//Make a list of words
    words.push_back("work");
    words.push_back("programming");
    words.push_back("code");
    words.push_back("car");
    words.push_back("home");
    words.push_back("lectures");
    words.push_back("exam");
    words.push_back("candies");
    words.push_back("death");
    words.push_back("project");
    words.push_back("robotics");
    words.push_back("christmas");

  }

void chooseWord(){

  //Select random word from list
        srand(time (NULL));
        int Random= rand() %words.size();

        randomWord = words[Random];

        ROS_INFO_STREAM(randomWord);

}


void result(){
  if(counterWrong+counterRight>=5){
    ROS_INFO_STREAM ("Number of correct answers: " << counterRight);
    ROS_INFO_STREAM ("Number of wrong answers: " << counterWrong);

    ros::shutdown();
  }
}


  int winner()
    {

      if (randomWord.length()!=guesses.length()){
        ROS_INFO("False");
        counterWrong++;
        result();
        chooseWord();
        return 0;
      }

        for(int i=0; i< randomWord.length(); i++) {
          if (randomWord[i]!=guesses[i]) {
              ROS_INFO("False");
              counterWrong++;
              result();
              chooseWord();
              return 0;
          }
        }
        ROS_INFO("True");
        counterRight++;
        result();
        chooseWord();
        return 1;
    }



  void sbCallback (const std_msgs::String::ConstPtr& msg){
    guesses=msg->data;
    winner();
  }



int main(int argc, char **argv) {

    ros::init (argc, argv, "subscriber");
    ros::NodeHandle nh;

    randomwords();
    chooseWord();

    sub = nh.subscribe("game", 10, sbCallback);

    ros::spin();
    return 0;

  }

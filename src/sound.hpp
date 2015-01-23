#ifndef SOUND_HPP__
#define SOUND_HPP__


using namespace std;

class Sound
{
private:
  string name_;
  string res_;

public:
  Sound(string name, string res) : name_(name), res_(res) { }
  void print()
  {
    cout << "Sound { name: " << name_ << ", res: " << res_ << " }" << endl;
  }
};
#endif

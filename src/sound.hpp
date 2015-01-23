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
  friend ostream& operator<<(ostream&, const Sound&);
};

ostream& operator<<(ostream& os, const Sound& rhs)
{
  os << "Sound { name: " << rhs.name_
     << " res: " << rhs.res_
     << " } ";

  return os;
}

#endif

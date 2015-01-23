#ifndef SOUND_HPP__
#define SOUND_HPP__

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>

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

  static Sound parse(boost::property_tree::ptree::value_type value)
  {
    return Sound(value.second.get<string>("<xmlattr>.name"),
                 value.second.get<string>("<xmlattr>.res"));
  }
};
#endif

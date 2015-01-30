#ifndef SOUND_HPP__
#define SOUND_HPP__

class Sound
{
private:
  std::string name_;
  std::string res_;

public:
  Sound(const std::string& name, const std::string& res)
    : name_(name), res_(res) { }

  inline std::string name() const { return name_; }
  inline std::string res() const { return res_; }

  friend std::ostream& operator<<(std::ostream&, const Sound&);
};

std::ostream& operator<<(std::ostream&, const Sound&);

#endif


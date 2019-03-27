#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
public:
  Cadena(unsigned t = 0, char c = ' ');
  Cadena(const Cadena &C);
  Cadena(const char *cadena);

  Cadena operator=(const Cadena &C);
  Cadena operator=(const char *cadena);
  operator const char *();
  Cadena operator+=(const Cadena &C);
  Cadena operator+(const Cadena &C);
  char operator[](int n);
  const char operator[](int n) const;

  char at(int n);
  const char at(int n) const;
  Cadena substr(unsigned indice, unsigned tamano);

  const unsigned length() const { return tam_; }

  ~Cadena();

private:
  char *s_;
  unsigned tam_;
};

bool operator==(const Cadena &C1, const Cadena &C2);
bool operator!=(const Cadena &C1, const Cadena &C2);
bool operator>(const Cadena &C1, const Cadena &C2);
bool operator<(const Cadena &C1, const Cadena &C2);
bool operator>=(const Cadena &C1, const Cadena &C2);
bool operator<=(const Cadena &C1, const Cadena &C2);

#endif
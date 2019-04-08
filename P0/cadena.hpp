#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
public:
  Cadena(unsigned t = 0, char c = ' ');
  Cadena(const Cadena &C);
  Cadena(const char *cadena);

  Cadena &operator=(const Cadena &C) noexcept;
  Cadena &operator=(const char *cadena) noexcept;
  operator const char *() const noexcept;
  Cadena &operator+=(const Cadena &C) noexcept;
  Cadena operator+(const Cadena &C) const noexcept;
  char &operator[](int n) noexcept;
  const char &operator[](int n) const noexcept;

  char &at(unsigned n);
  const char &at(unsigned n) const;
  Cadena substr(unsigned indice, unsigned tamano) const;

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
#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha
{
  public:
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const Fecha &F) = default;
    Fecha(const char *fecha);

    Fecha &operator++();
    Fecha operator++(int);
    Fecha &operator--();
    Fecha operator--(int);
    Fecha &operator+(int) const;
    Fecha &operator-(int) const;

    Fecha &operator-=(int);
    Fecha &operator+=(int);
    Fecha &operator=(const Fecha &F) = default;
    
    operator const char *() const;

    int dia() const noexcept { return dia_; }
    int mes() const noexcept { return mes_; }
    int anno() const noexcept { return anno_; }

    class Invalida
    {
      public:
        Invalida(const char *error) : error_(error) {}
        const char *por_que() const noexcept { return error_; }

      private:
        const char *error_;
    };

  private:
    int dia_, mes_, anno_;
    void valida() const;
};

bool operator==(const Fecha &F1, const Fecha &F2) noexcept;
bool operator!=(const Fecha &F1, const Fecha &F2) noexcept;
bool operator>(const Fecha &F1, const Fecha &F2) noexcept;
bool operator<(const Fecha &F1, const Fecha &F2) noexcept;
bool operator>=(const Fecha &F1, const Fecha &F2) noexcept;
bool operator<=(const Fecha &F1, const Fecha &F2) noexcept;

#endif
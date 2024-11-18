#ifndef MARCO_PAGINA_H
#define MARCO_PAGINA_H

class Marco{
private:
    int id;
    bool bit_referencia;
public:
    Marco(int);
    int getId();
    bool getRefBit();
    void setRefBit(bool);
};

#endif
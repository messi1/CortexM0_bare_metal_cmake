//#include <type_traits>

// define used registers
static volatile unsigned &RCC_AHB1 = *reinterpret_cast<unsigned *>(0x40021014);
static volatile unsigned &GPIOA_MODER =
    *reinterpret_cast<unsigned *>(0x48000000);
static volatile unsigned &GPIOA_BSRR =
    *reinterpret_cast<unsigned *>(0x48000018);

class A {
public:
  virtual void bla() = 0;
  virtual void gugus() = 0;
};

class B : public A {
public:
  void bla() override {}
  void gugus() override {}
};

// application
int main_app() {
  B ab;
  ab.gugus();
  volatile int x = static_cast<int>(100000l);
  static_assert(1<2);
  if (x)
    ++x;
  RCC_AHB1 |= 0x00020000;    // enable clock for GPIOA
  GPIOA_MODER |= 0x40000000; // set output on GPIOA.P15
  // double x = 0.0;
  // double y = 0.0;
  volatile int *bla = new int;

  if (bla) {
    *bla = 10;
  }

  for (int i = 0; i < 10; ++i) {
    *bla = 10 + i;
  }

  while (true) {
    // y = sin(x);
    // x += y;
    GPIOA_BSRR = 0x00008000; // set output on GPIOA.P15
    GPIOA_BSRR = 0x80000000; // clear output on GPIOA.P15
  }
  return 0;
}

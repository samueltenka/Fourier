#include "Cepstrum.h"

int main(int argc, char** argv) {
   Array<filename> ins(3);
   ins.data[0] = "Audio/oooh0138_00.wav";
   ins.data[1] = "Audio/oooh0138_01.wav";
   ins.data[2] = "Audio/oooh0138_02.wav";
   filename out = "Audio/oooh0138_allavgd.wav";
   extract_essence(ins, out);
   return 0;
}

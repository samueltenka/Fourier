from math import pi,cos,sin

N=256
thetas = (2*pi*float(i)/N for i in range(N))
text = '{'+',\n'.join('Cmplx('+str(cos(th))+','+str(sin(th))+')' for th in thetas)+'}'
with open('expi_table.dat','w') as f:
   f.write(text)

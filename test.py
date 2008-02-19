#!/usr/bin/env python
from Adolc import *

#constructors
a = adouble(13.);	print 'a=adouble(13.)\t= ',a,'\t\ta.val =',a.val
b = adouble(5);		print 'b=adouble(5)\t= ',b,'\t\tb.val =',b.val

#unary
print '-a  \t =',-a
print '+a  \t =',+a

#operator + for int and double
print 'a+2  \t =',a+2
print 'a+2. \t =',a+2.
print '2+a  \t =',2+a
print '2.+a \t =',2.+a

#operator - for int and double
print 'a-2  \t =',a-2
print 'a-2. \t =',a-2.
print '2-a  \t =',2-a
print '2.-a \t =',2.-a

#operator * for int and double
print 'a*2  \t =',a*2
print 'a*2. \t =',a*2.
print '2*a  \t =',2*a
print '2.*a \t =',2.*a

#operator / for int and double
print 'a/2  \t =',a/2
print 'a/2. \t =',a/2.
print '2/a  \t =',2/a
print '2./a \t =',2./a

#operator +,-,*,/ for badouble
print 'a+b  \t =',a+b
print 'a-b  \t =',a-b
print 'a*b  \t =',a*b
print 'a/b  \t =',a/b

#operator +=,-=,*=,/= for badouble
a+=b; print 'a+=b  \t =',a
a-=b; print 'a-=b  \t =',a
a*=b; print 'a*=b  \t =',a
a/=b; print 'a/=b  \t =',a

#functions
import numpy as npy
a = adouble(0.4)
print 'exp  (a)', npy.exp  (a), a.exp  ()
print 'log  (a)', npy.log  (a), a.log  ()
print 'sqrt (a)', npy.sqrt (a), a.sqrt ()
print 'sin  (a)', npy.sin  (a), a.sin  ()
print 'cos  (a)', npy.cos  (a), a.cos  ()
print 'tan  (a)', npy.tan  (a), a.tan  ()
print 'asin (a)', 				a.asin ()
print 'acos (a)',				a.acos ()
print 'atan (a)',				a.atan ()
print 'log10(a)',				a.log10()


print 'a**2.', a**2.
print 'a**2', a**2
print "to be implemented print '2.**a', 2.**a"














def speelpenning(avec):
	tmp = avec[0]
	for a in avec:
		tmp *= a
	return tmp

import numpy as npy
ax = npy.array([adouble(i) for i in range(1,4)])
x = npy.array([1.*i for i in range(1,4)])
trace_on(1)
for i in range(npy.shape(ax)[0]):
	 ax[i].is_independent(x[i])#equivalent to ax[i]<<=x[i]
A = 4*npy.ones((3,3))
ax = npy.dot(A,ax)
ay = speelpenning(ax)
y = depends_on(ay)
trace_off()

#print y
#print x

print 'shape(x)=',npy.shape(x)
print 'Adolc\tfunction evaluation:\t',function(1,1,x)
print 'normal\tfunction evaluation:\t',speelpenning(x)

g = gradient(1,x)

print 'gradient is', g

from __future__ import division, print_function
N=int(1000000)
A=[0]*N
A[0]=(1.0/2.0)
for i in xrange(1,N):
    A[i] = A[i-1] + (i+(1.0/4.0))**(1/2)
def fun(n):
    if(n<N):
        return A[n]
    return (2.0/3.0)*(n**(3.0/2.0))

def calc(n):
    tmp = n-2.0+2.0*fun(n-1)
    return 1.0/(2.0*n) * (n-2.0+2.0*fun(n-1))

for x in xrange(input()):
    print(calc(input()))


import math#continued to basics oct 30, 2019
def areaofcircle(r):# so need top give value of r
    PI = 3.1416
    return (PI * r* r) 
print ("Area of circle is %.6f" % areaofcircle(19))

def area_square(l):
    return(l*l)
print("Area of square is %.2f" % area_square(25.67) )


c = 3 *100000000
def energy(p,m):
    return(math.sqrt(p*p *c *c + m *m *c *c *c *c))
print("energy = %.4f" % energy(2.6, 2.6))

#one number ^ (other number)
def power(x,y):
    return(x**y)
print("x to the power y is = %.3f" % power(6,3))


#4^4
print (4**4)

m= 20.
n =90.
print (m/n)
print (m*n)
print (m**n)
print(n % m) # remainder of 90/20

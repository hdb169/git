#four will be totally from https://www.youtube.com/watch?v=_uQrJ0TkZlc

#types of numbers:
price = 10 #integers
print(price)
price = 20
print(price)
rating = 4.9 #floats
name = 'Bidhan'# string
is_published = False #Boolians


full_name = 'Bidhan Bhatt'
age = 3
is_playing = True
"""
#this works good, input means you should type in the terminal, commented for now
Name = input('What is your name? ')
favorite_color = input('What is is favorite color?' )
time = input('What time do you get up? ')
print(Name + ' likes ' + favorite_color + ' and' +  ' getup early at ' + time)
"""

"""
#asking about age, convert float into integer
birth_year = input (' Birth year: ' )
age = 2019 - int(birth_year)
#print =( 'birth year = ' + birth)
print(age)
print( type(birth_year))
print(type(age))

"""


#weight and convert to pound

weight_lbs = 134 #input( ' weight (lbs) ')
weight_kg = int(weight_lbs) * 0.453592
print (weight_kg)
print('My weight is ' + str(weight_lbs) + ' pounds  and it is ' + str( weight_kg ) + str (' kg. '))
# you are printing a sentence and it cant't be integer so convert everything into str
# if you remove the input, you don't need to type in terminal. 


course = ("python's course for 'beginners' ")# single vs double quotes
print(course)
email = '''
Hi John,

this is my first email to you. Lets be in touch.

Thanks.
Best Regards,
Hem
'''
print(email)

print(course[10])# print 10th character
print(course[-4])#4th from last
print(course[0:50])#print all from 0 to 6th character
#print(course[start index: ending index=length of word])
another = course[:]#print everything in course
print(another)
sand = course[10:50]
print(sand)

yat = email[:]
print(yat)

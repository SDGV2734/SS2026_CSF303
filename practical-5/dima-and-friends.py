n = int(input())                           
friends = list(map(int, input().split()))  

sum_friends = sum(friends)                 

total_people = n + 1                       
count = 0                                  

for d in range(1, 6):                      
    grand_total = sum_friends + d          
    lands_on = grand_total % total_people  
    if lands_on != 1:                     
        count += 1                         

print(count)
n = int(input())               

goals = {}                     

for i in range(n):              
    team = input()             
    if team in goals:           
        goals[team] += 1       
    else:                       
        goals[team] = 1        

winner = max(goals, key=goals.get)  
print(winner)                       
## Download numpy library before running the code
import numpy as np

print("Input the Reach Number ")
reach_num = int(input())
print("Input the max Range")
a = int(input())
print("The game starts now!!!")
print(f"The player who reaches {reach_num} first wins the game")
print(f"Remember: You can only add a number between 1 to {a} both 1 and {a} inclusive")

## Making user to be first player and computer to be second player
def startGame(win_pattern, reach_num, a):
  sum = 0
  print("You are the first player to start")
  while (sum < reach_num):
    print("*" * 70)
    print(f"\nIts your chance to add any number between 1 to {a}")
    user = int(input())
    if user > a or user<1:
      print("Input is not in range")
      print(f"Add another number which is in range [1,{a}]")
      continue
    sum = adder(sum, "User", user)
    if sum >= reach_num:
      winner = "User"
      print("\n","-" * 70)
      print("Congrats you defeated a machine \nYou are the winner of this game !!!!") 
      break
    computer = best_move(win_pattern, sum, a)
    sum = adder(sum, "Computer", computer)
    if sum >= reach_num:
      winner = "Computer"
      print("\n","-" * 70)
      print("Sorry but the Winner of this game is ", winner, "!!!!")
      print("Better Luck next time.")
      break


def adder(sum, player, num):
  if player == "User":
    print("\nYou decided to add ", num)
    print("Sum = ", sum, " + ", num)
    sum += num
    print("Current sum = ", sum)
  else:
    print("\nComputer decided to add ", num)
    print("Sum = ", sum, " + ", num)
    sum += num
    print("Current sum = ", sum)
  return sum


def best_move(win_pattern, sum, maxAdd):
  for i in range(len(win_pattern)):
    if sum == win_pattern[i]:
      return np.random.randint(1, maxAdd + 1)
    if sum < win_pattern[i]:
      break
  return win_pattern[i] - sum


def winArray(reach_num, a):
  i = reach_num
  win_lst = []
  while (i > 0):
    win_lst = [i] + win_lst
    i = i - a - 1
  return win_lst


win_pattern = winArray(reach_num, a)
startGame(win_pattern, reach_num, a)

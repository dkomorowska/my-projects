import random

print("Welcome to rock paper scissors game!")
print("------------------------------------")

player_points = 0
computer_points = 0

how_many_rounds = int(input("How many rounds do you want to play? "))

for i in range(how_many_rounds):
    print(f"\nRound {i + 1}:")
    print("Choose:")
    print("1 - rock")
    print("2 - paper")
    print("3 - scissors")

    choice = input("Your choice (1/2/3): ")

    if choice == "1":
        player_choice = "rock"
    elif choice == "2":
        player_choice = "paper"
    elif choice == "3":
        player_choice = "scissors"
    else:
        player_choice = "invalid choice"

    computer_options = ["rock", "paper", "scissors"]
    computer_choice = random.choice(computer_options)

    print(f"You chose: {player_choice}")
    print(f"Computer chose: {computer_choice}")

    if player_choice == computer_choice:
        print("It's a tie!")
    elif player_choice == "rock" and computer_choice == "scissors":
        print("You win! Rock crushes scissors")
        player_points = player_points + 1
    elif player_choice == "paper" and computer_choice == "rock":
        print("You win! Paper covers rock")
        player_points = player_points + 1
    elif player_choice == "scissors" and computer_choice == "paper":
        print("You win! Scissors cut paper")
        player_points = player_points + 1
    else:
        print("You lose!")
        computer_points = computer_points + 1

#summary
print("\n===================================")
print("GAME OVER!")
print(f"Your points: {player_points}")
print(f"Computer points: {computer_points}")

if player_points > computer_points:
    print("CONGRATULATIONS! YOU WON!")
elif player_points < computer_points:
    print("Sorry, you lost...")
else:
    print("IT'S A TIE!")

print("Thanks for playing!")
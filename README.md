# C-Jam-SportsTrivia
A sports trivia game for the C game-jam. https://itch.io/jam/c-jam

This game has been developed to pay tribute to 50 years of the C language.

## Description

Version 1.0 of the game includes 20 questions.

The game takes place between 2 players. Each player will have to answer 5 questions randomly selected  from the 20 questions.

You will hear the bell when you get the correct answer or the buzzer otherwise.

The game ends after all 10 questions have been answered.

You can download the binaries here : https://jedubuntu.itch.io/sports-trivia

## Install instructions
Download the snap file
Navigate to the folder where you saved the file
sudo snap install sportstrivia_1.0_amd64.snap --dangerous
Yes I know the --dangerous may seem quite strange but it's just that the package is not signed
sudo snap connect sportstrivia:alsa
This step is required to connect the audio interface to the game
Then type sportstrivia to launch the game
Enjoy!

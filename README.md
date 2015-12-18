# BasicQt

This repository contains a training task for basics of using Qt.

## Aim of the exercise
Write a simple application that models a producer-consumer problem.
Upon request from the application, the producer shall spawn worker threads, that create data.
These are then given to the consumer who in turn spawns worker threads to handle the given data items.

## How to proceed
First, get an overview over all the files involved. Some already contain a bunch of TODOs and further details.
The best approach would be to implement a most simple producer and consumer worker and slowly complete the TODOs
Then you can add finer detail and more features.

##Notes
* Check often that your application still compiles.
* Also check regularly if the application runs as intended.
* Linker errors (especially related to moc) may result from the fact, that the QtCreator does not purge Makefiles from the build directory. 
Clean the whole build directory manually and try again.

##Can I win something?
* You are allowed to cooperate and work together.
* The person or the group of persons delivering the best code will be considered the winner
* There will be cake (of your choice)
* I am not joking
* Deadline for cake-eligibility is the [Mungday, a Setting Orange, the fifth day of Chaos](https://en.wikipedia.org/wiki/Discordian_calendar) at midnight.

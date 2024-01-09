# <Bullet Hell>

## Description
- What was your motivation = Improv performance and add a observer pattern into the project. Also the code had preconfigured calculations that were heavy during the profiler ( Example using the POW method ). 
- Why did you build this project?
  Because i believe it's important to improv my skills and also understand how to work with other peoples code.
- What problem does it solve?
  Using the observer pattern allows cleaner code but also making the code not interact with each other when it's not necessary.
  Never ending missles caused a large amount of missles to appear, Pooling the missles to increase performances.
  AA BB collision detection improvement.
  Missile::update()	Lineare (O(N)
  World::updateEntities(),    quadratique   (O(N^2)
  World::removeDeadEntities ()	              Lineare (O(N)
  CollisionManager::checkCollisions()	    quadratique   (O(N^2)

  ![image](https://github.com/robbyseguin/Observer-Class-Raylib/assets/100798593/e56014f5-53ad-4ee7-abc3-c1b33edd801e)


  
- What did you learn?
  That it's important to watch how the BIG O performances when using for loops, Design patterns are a must when used correctly. Proper use of the profiler is an amazing tool for gameplay programmer

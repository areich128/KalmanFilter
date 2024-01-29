# KalmanFilter
Developing a Kalman filter algorithm to build my experience with them before working on avionics for spaceshot this spring.

As I go through the process of developing this algo, I am following [this](https://www.kalmanfilter.net/alphabeta.html) tutorial.



## $\alpha$ - $\beta$ - $\gamma$ Filter:

This type of filter is used in the tutorial as a lead-up to the Kalman filter. While the Kalman filter treats each variable as random and uses standard distributions to create an estimate, the $\alpha$ - $\beta$ - $\gamma$ filter uses known system state equations (in this case, simple kinematic equations).

The filter makes use of two important equations for each variable (position, velocity, and acceleration): 

### 1. State Update Equation:

The point of these equations are to update our estimate of the true quantity considering a new measurement and that time has passed. The coefficients can be changed based on sensor accuracy.

**For POSITION:**

$position_{est} = position_{pred} * \alpha (measurement_{n} - position_{pred})$

**For VELOCITY:**

$velocity_{est} = velocity_{pred} * \beta (\frac{measurement_{n} - position_{pred}}{\Delta t})$

**For ACCELERATION:**

$acceleration_{est} = acceleration_{pred} * \gamma (\frac{measurement_n - position_{pred}}{0.5 (\Delta t)^2})$


- $example_{est}$ represents the Kalman filter's guess on the state.
- $example_{pred}$ is given by the state prediction made in the previous time step.
- $\alpha$, $\beta$, and $\gamma$ are the gains. If the measurement accuracy is high, alpha/beta should approach 1, as this will make the measurement influence the equation more. If the measurement accuracy is low, alpha/beta should approach 0 for the same reason.
- $measurement_n$ is the position measurement taken by the sensor at time n. In my code, this is represented by a time series array.

### 2. State Extrapolation Equation:

This equation is given by the system-- in this case, we are using 1d kinematics. This gives us the equation:

$x_f = x_i + (v  \Delta t) + 0.5 a (\Delta t)^2$

$v_f = v_i + a \Delta t$

$a_f = a_i$ (assuming constant acceleration)

where $\Delta t$ is the sampling period.


This filter is very useful if the system is relatively simple, and the equations governing the system dynamics are known. However, most real life systems have more unpredictability and extremely complicated equations, which is why the Kalman filter is widely used.




Sources: 
[michaelscheinfeild](https://medium.com/@michaelscheinfeild/alpha-beta-gamma-and-kalman-filter-bfd21041d940),
[Kalman Filter from the Ground Up: Alex Becker](https://www.kalmanfilter.net/kalman1d.html), 
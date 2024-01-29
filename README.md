# KalmanFilter
Developing a Kalman filter algorithm to build my experience with them before working on avionics for spaceshot this spring.

As I go through the process of developing this algo, I am following [this](https://www.kalmanfilter.net/alphabeta.html) tutorial.

There are 5 main equations for the Kalman filter:

## 1. State Update Equation:

**For POSITION:**

$estimated = predicted * \alpha (measurement_{n} - predicted)$

**For VELOCITY:**

$estimated = predicted * \beta (\frac{measurement_{n} - predicted}{\Delta t})$

**For ACCELERATION:**

$estimated = predicted * \gamma (\frac{measurement_n - predicted}{0.5 (\Delta t)^2})$


- $estimated$ represents the Kalman filter's guess on the state.
- $predicted$ is given by the state prediction made in the previous time step.
- $\alpha$ is the Kalman gain. If the measurement accuracy is high, alpha/beta should approach 1, as this will make the measurement influence the equation more. If the measurement accuracy is low, alpha/beta should approach 0 for the same reason.
- $measurement_n$ is the measurement taken by the sensor at time n. In my code, this is represented by a time series array.

## 2. State Extrapolation Equation:

This equation is given by the system-- in this case, we are using 1d kinematics. This gives us the equation:

$x_f = x_i + (v  \Delta t)$

where $x_f$ is the predicted position, $x_i$ is the initial position for that time step, $v$ is the estimated velocity, and $\Delta t$ is the sampling period.





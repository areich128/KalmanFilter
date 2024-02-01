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

## The Kalman Filter

This filter uses the state update equations but also accounts for the variance in the various measurements. This allows the algorithm to converge close to the true value.

It does this by not only predicting the various system states (position, velocity, acceleration etc.), but also the *VARIANCE* of those system states. In other words, it uses the measured states and respective variances, as well as the *estimated* states and variances.

### Version 1: Constant Dynamics With No Process Noise

There are two types of noise that can affect measurements that the Kalman filter can account for. 
- **Measurement Noise:** This is noise caused by the error in the measurement due to sensor inaccuracy.
- **Process Noise:** This is noise caused by external impacts that change the physical state of the system. For example, if we are measuring the position of a plane, wind might create process noise.

We still follow the general algorithm:

0. Initialize
1. Measure
2. Update
3. Predict

and then loop over 1, 2, and 3 for all the data points in the set.

We get the following 5 equations:

#### State Update Equations:
1. **State Equation:** 

$x_{est} = x_{pred} + K_n (z_n - x_{pred})$

2. **Covariance Update Equation:**

$var = (1 - K_n) var_{pred}$

3. **Kalman Gain Equation:**

$K_n = \frac{var_{pred}}{var_{pred} + r_n}$

#### State Prediction Equations:

4. **State Extrapolation Equation:** This equation updates the estimate for the variable according to the system dynamics. In the examples here this is either constant or in accordance with simple kinematics.

5. **Covariance Extrapolation Equation:** This equation does the same thing as the State Extrapolation Equation, but instead of updating the estimate for the state, it updates the estimate for the *covariance* of the estimated state. With process noise added, whatever covariance is of the highest degree/constant should be += with process noise covariance.

### Process Noise Details:

If we use the constant dynamic system to measure something with a constant increase, for example the temperature of a pot of water heating up linearly using a small process noise covariance, we will get a lag error.
- This means that while the Kalman Filter will eventually converge on the correct slope, the actual values will lag behind the true values by a potentially significant amount.

We can fix this, even if our system dynamics are not well defined. **Increasing the process noise variance** is the key.



Sources: 
[michaelscheinfeild](https://medium.com/@michaelscheinfeild/alpha-beta-gamma-and-kalman-filter-bfd21041d940),
[Kalman Filter from the Ground Up: Alex Becker](https://www.kalmanfilter.net/kalman1d.html), 
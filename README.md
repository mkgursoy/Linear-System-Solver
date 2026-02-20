# Linear-System-Solver

A linear system solver written in C++ using the Gauss–Jordan Elimination algorithm, including two separate implementations designed for different variations of the problem.

---


## Integer (Exact Rational) Solver

Given a system consisting of integar coefficients it calculates the number of solutions, and a possible solution giving values in form of fractions. (Numerator / Denominator)

It also finds out a possible Row Echelon Form, and the Reduced Row Echelon Form of the input Augmented Matrix.

This version works slower than the other, because of precise fractal calculations.

### Problem Form

Given a system:

A₁,₁ x₁ + A₁,₂ x₂ + A₁,₃ x₃ + ... + A₁,ₙ xₙ = b₁  
A₂,₁ x₁ + A₂,₂ x₂ + A₂,₃ x₃ + ... + A₂,ₙ xₙ = b₂  
⋮  
Aₘ,₁ x₁ + Aₘ,₂ x₂ + Aₘ,₃ x₃ + ... + Aₘ,ₙ xₙ = bₘ  

where:

- A is an m × n matrix of integers
- x is a vector of unknowns
- b is a vector of integers

---

## Modular Solver

Given a system consisting of integar coefficients it calculates the number of solutions, and a possible solution giving values in form of integars.

It also finds out a possible Row Echelon Form, and the Reduced Row Echelon Form of the input Augmented Matrix.

### Problem Form

Given a system:

A₁,₁ x₁ + A₁,₂ x₂ + A₁,₃ x₃ + ... + A₁,ₙ xₙ ≡ b₁ (mod M)  
A₂,₁ x₁ + A₂,₂ x₂ + A₂,₃ x₃ + ... + A₂,ₙ xₙ ≡ b₂ (mod M)  
⋮  
Aₘ,₁ x₁ + Aₘ,₂ x₂ + Aₘ,₃ x₃ + ... + Aₘ,ₙ xₙ ≡ bₘ (mod M)

or equivalently:

A x ≡ b (mod M)

where:

- A is an m × n matrix of integers
- x is a vector of unknowns
- b is a vector of integers

# Assigment 2 - HPC 039

* Earl Fernando Panimayam Fernando
* Anand
* Anoop







## Benchmarks
### Single thread with 1000 lines 

|Polynomial  | 1       | 2       |5        |7        | 
|:-----------|:-------:|--------:|:-------:|--------:|
|Actual time | 0.073   |  0.125  | 0.285   | 0.496   |
|Max runtime | 1.01    | 1.48    | 1.52    | 1.64    |




### Multi-threaded with 1000 lines and polynomial x^5-1

|Threads     | 1       | 2       |3        |4        | 
|:-----------|:-------:|--------:|:-------:|--------:|
|Actual time | 0.285   |  0.148  | 0.104   | 0.078   |
|Max runtime | 1.52    | 0.70    | 0.55    | 0.42    |



### 10 Threads and polynomial degree of 7

|Lines        | 1000    | 50000  |
|:------------|:-------:|-------:|
|Actual time  | 0.058   |121.192 |
|Max runtime  | 0.26    |594     |


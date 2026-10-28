# Test plan

Each row is one named cmocka test. Expected results come from the written specification.

| Minutes  | Expected          | Reason for the test                  |
| -------- | ----------------- | ------------------------------------ |
| −1       | −1 (error)        | Just below the valid range           |
|  0       |  0 cents          | Free parking boundary                |
|  1       |  500 cents ($5)   | First chargeable minute              |
|  30      |  500 cents ($5)   | Representative within the first hour |
|  59      |  500 cents ($5)   | Just before the first hour ends      |
|  60      |  500 cents ($5)   | Exactly one hour                     |
|  61      |  700 cents ($7)   | Second started hour                  |
|  119     |  700 cents ($7)   | Just before the second hour ends     |
|  120     |  700 cents ($7)   | Exactly two hours                    |
|  121     |  900 cents ($9)   | Third started hour                   |
|  1440    |  5100 cents ($51) | Largest accepted duration            |
|  1441    | −1 (error)        | Just above the valid range           |

Selected equivalence partitions include negative durations, zero, each 
started-hour interval, and durations above 1440. Boundary examples surround 
0/1, 60/61, 120/121, and the accepted upper limit. This suite samples the 
repeating hourly rule and does not claim complete boundary or structural coverage.

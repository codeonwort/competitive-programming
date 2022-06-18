-- ID : 1697A (Parkway Walk)
-- URL: https://codeforces.com/problemset/problem/1697/A

import Control.Monad

readInt = read `fmap` getLine :: IO Int
readInts = map read `fmap` words `fmap` getLine :: IO [Int]

main = readInt >>= \t -> replicateM_ t $ readInts >>= \[n,m] -> readInts >>= \as -> print (max (sum as - m) 0)

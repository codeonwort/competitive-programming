-- ID  : 1569B (B. Chess Tournament)
-- URL : https://codeforces.com/contest/1569/problem/B

import Control.Monad
import Data.Array
import Data.List

readInt = read `fmap` getLine :: IO Int

main = readInt >>= \t -> replicateM_ t solve

{-
 - For those who don't wanna lose any game, assign draw for their every matches.
 - For those who wanna win at lesat one game, they can form a cycle
   s.t. each former wins against its latter (must be n >= 3)
-}
solve = do
    n <- readInt
    desires <- zip [1..n] `fmap` getLine
    let (winners,noLosers) = partition (\(i,x) -> x == '2') desires
    let winCycle = zip xs (tail xs ++ [head xs]) where xs = map fst winners
    let drawCycle = map (\(i,x) -> (i,0)) noLosers
    let strat = array (1,n) (winCycle ++ drawCycle)
    -- print strat
    let numWinners = length winners
    let numNoLosers = n - numWinners
    if numWinners == 1 || numWinners == 2 then putStrLn "NO"
    else do
        -- Cumbersome but works...
        let m = array ((1,1),(n,n)) [((i,j),f (strat ! i) i j) | i <- [1..n], j <- [1..n]] where
            f strat i j
                | i == j      = 'X'
                | strat == 0  = '='
                | strat == i  = '-'
                | strat == j  = '+'
                | otherwise   = '='
        let m2 = array ((1,1),(n,n)) [((i,j),f i j (m ! (i,j))) | i <- [1..n], j <- [1..n]] where
            f i j x
                | x /= '='  = x
                | otherwise = invert (m ! (j,i))
            invert x
                | x == '-'  = '+'
                | x == '+'  = '-'
                | otherwise = x
        putStrLn "YES"
        forM_ [1..n] $ \i -> do
            forM_ [1..n] $ \j -> do
                putChar (m2 ! (i,j))
            putChar '\n'


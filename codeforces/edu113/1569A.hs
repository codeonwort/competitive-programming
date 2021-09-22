-- ID  : 1569A (Balanced Substring)
-- URL : https://codeforces.com/contest/1569/problem/A

import Control.Monad
import Data.Array

readInt = read `fmap` getLine :: IO Int

isA x = if x == 'a' then 1 else 0
isB x = if x == 'b' then 1 else 0

-- Same solution as the C++ version.
main = do
    t <- readInt
    replicateM_ t $ do
        n <- readInt
        msg <- getLine :: IO [Char]
        let numA = listArray (0,n) $ scanl (+) 0 (map isA msg)
        let numB = listArray (0,n) $ scanl (+) 0 (map isB msg)
        let solns = filter balanced [(x,y) | x <- [1..n], y <- [x..n]] where
            balanced (x,y) = (numA ! y) - (numA ! (x-1)) == (numB ! y) - (numB ! (x-1))
        if null solns then do
            putStrLn "-1 -1"
        else do
            let (x,y) = head solns
            putStrLn $ (show x) ++ " " ++ (show y)

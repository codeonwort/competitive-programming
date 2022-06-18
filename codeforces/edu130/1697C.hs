-- ID : 1697C (awoo's Favorite Problem)
-- URL: https://codeforces.com/problemset/problem/1697/C

-- NOTE: Had no idea how to solve it, looked over the solution X(

{-# LANGUAGE CPP #-}
#define ENABLE_TRACE 0


import Control.Monad
#if ENABLE_TRACE
import Debug.Trace (trace)
#endif

-- IO util
import qualified Data.ByteString.Char8 as BS8
import qualified Data.ByteString as BS
readInt = read `fmap` getLine :: IO Int

#if !ENABLE_TRACE
trace a b = b
#endif

main = do
    q <- readInt
    replicateM_ q solve

solve = do
    n <- readInt
    src <- getLine
    dst <- getLine
    let b1 = length . filter (== 'b') $ src
    let b2 = length . filter (== 'b') $ dst
    if (b1 == b2) && (f 0 0 n src dst)
        then putStrLn "YES"
        else putStrLn "NO"

fmt c i j n xs ys = c ++ ": " ++ show [i,j,n] ++ ", " ++ xs ++ ", " ++ ys

f i j n src dst
    | i >= n           = trace (fmt "case1" i j n src dst) $ True
    | x == 'b'         = trace (fmt "case2" (i+1) j n xs dst) $ f (i+1) j n xs dst
    | (x /= y') || (x == 'a' && i > j') || (x == 'c' && i < j') = False
    | otherwise        = trace (fmt "case4" (i+1) j'' n xs ys'') $ f (i+1) j'' n xs ys''
    where
        (x:xs) = src
        (y:ys) = dst
        bs = leadingB dst
        j' = j + bs
        (y':ys') = drop bs dst
        j'' = min n (j'+1)
        ys'' = if j'' == n then [] else ys'

leadingB ys = f 0 ys where
    f n ('b':yys) = f (n+1) yys
    f n _ = n


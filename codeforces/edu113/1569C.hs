-- ID  : 1569C (C. Jury Meeting)
-- URL : https://codeforces.com/contest/1569/problem/C
-- Failed to solve on my own and saw the editorial :/

import Control.Monad

-- bytestring for fast IO
import Data.Int
import Data.Maybe
import qualified Data.ByteString.Char8 as BS8
import qualified Data.ByteString as BS
getInt = parseInt `fmap` BS8.getLine :: IO Int64
getInts = (map parseInt . BS8.words) `fmap` BS8.getLine :: IO [Int64]
parseInt = fromIntegral . fst . fromJust . BS8.readInt

main = do
    t <- getInt
    replicateM_ (fromIntegral t) solve

magic = 998244353
mul2 x y = (x * y) `mod` magic

{- NOTE on Int64
 - 
 - It's strange but when I use just Int type, codeforces and my desktop give different results for the input:
 - n = 74
 - as = 9 3 10 8 6 6 1 6 9 3 7 3 2 8 1 5 8 4 6 4 1 6 5 6 10 3 6 6 6 4 9 5 8 7 2 1 6 2 4 9 10 9 5 4 7 5 7 2 10 10 1 5 2 4 1 7 7 3 8 10 2 5 8 4 3 9 2 9 9 8 6 8 4 5
 - The answer is 420779088 and my desktop gives that number but codeforces gives 939628924.
 - Switching every Int to Int64 fixes the problem but I don't know why? Even the solution in the editorial uses int, not int64_t.
 -}
solve = do
    n <- getInt
    as <- getInts
    let maxima = maximum as
    let k = fromIntegral $ length $ filter (== (maxima - 1)) as
    let maxima_count = length $ filter (== maxima) as
    let x = foldl1 mul2 [1..n]
    let y = foldl1 mul2 [m | m <- [1..n], m /= (k + 1)]
    let answer = if maxima_count == 1 then (x - y + magic) `mod` magic else x
    print answer

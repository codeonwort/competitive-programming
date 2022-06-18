-- ID : 1697B (Promo)
-- URL: https://codeforces.com/problemset/problem/1697/B

import Control.Monad
import Data.List
import Data.Array

-- Fast IO
import Data.Int
import Data.Maybe
import qualified Data.ByteString.Char8 as BS8
import qualified Data.ByteString as BS
getInt64 = parseInt `fmap` BS8.getLine :: IO Int64
getInt64s = (map parseInt . BS8.words) `fmap` BS8.getLine :: IO [Int64]
parseInt = fromIntegral . fst . fromJust . BS8.readInt
-- Slow IO
getIntsSlow = (map read . words) `fmap` getLine :: IO [Int]

main = do
    [n,q] <- getIntsSlow
    ps0 <- getInt64s
    let ps = sortBy (\a b -> compare b a) ps0
    let subsumTable = listArray (0,n) (scanl (+) 0 ps) :: Array Int Int64
    --print subsumTable
    replicateM_ q $ do
        [x,y] <- getInt64s
        let answer = (subsumTable ! (fromIntegral x)) - (subsumTable ! (fromIntegral (x-y)))
        print answer

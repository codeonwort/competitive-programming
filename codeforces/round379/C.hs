-- Codeforces Round #379 (Div. 2)
-- http://codeforces.com/contest/734

-- ID: 734C (Anton and Making Potions)

import Control.Monad
import Data.Array
import Data.Int
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt64s = (map (fromIntegral . fst . fromJust . BS8.readInteger) . BS8.words) `fmap` BS.getLine :: IO [Int64]

main = do
	[n, m, k] <- getInt64s
	[x, s] <- getInt64s
	as <- (listArray (0, m-1)) `fmap` getInt64s
	bs <- (listArray (0, m-1)) `fmap` getInt64s
	cs <- (listArray (0, k-1)) `fmap` getInt64s
	ds <- (listArray (0, k-1)) `fmap` getInt64s
	let ub = upperBound ds k s
	let freePotion = cs ! (ub - 1)
	let noFirst = if ub > 0 then (max (n - freePotion) 0) * x else n * x
	let bestUsingFirst = minimum $ map (make as bs cs ds n k s) [0..m-1]
	print $ min noFirst bestUsingFirst

make as bs cs ds n k s i
	| bs ! i > s = maxBound :: Int64
	| otherwise = (max 0 remain) * (as ! i)
	where
		remain = n - (if ub == 0 then 0 else (cs ! (ub - 1)))
		ub = upperBound ds k (s - bs ! i)


upperBound :: Array Int64 Int64 -> Int64 -> Int64 -> Int64
upperBound ary n x = go 0 n where
	go lb ub
		| lb >= ub = ub
		| ary ! mid <= x = go (mid+1) ub
		| ary ! mid > x = go lb mid
		where mid = (lb + ub) `div` 2

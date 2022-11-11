import Data.Maybe
import Data.Array
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.IntSet as Set
--import Debug.Trace

-- ID:	703B (Mishka and Trip)
-- URL:	http://codeforces.com/contest/703/problem/B

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	[n,k] <- getInts
	costs <- getInts
	capitals <- getInts
	let costs' = listArray (1,n) costs
	let totalCost = sum (map fromIntegral costs) :: Integer
	let capitalTotalCost = sum (map (\i -> fromIntegral (costs' ! i)) capitals) :: Integer
	let capitalSet = foldl addCapital Set.empty capitals 
	print $ solve n k costs' capitalSet totalCost capitalTotalCost
	
addCapital set capital = Set.insert capital set

solve n k costs capitals totalCost capitalTotalCost = (f [1..n] (0::Integer)) `div` 2 where
	f [] acc = acc
	f (i:is) acc
		| Set.member i capitals = f is (acc + (ci * (totalCost - ci)))
		| otherwise = f is acc'
		where
			acc' = acc + fromIntegral (ci * (cnext + cprev + capitals'))
			ci = fromIntegral (costs ! i) :: Integer
			capitals' = capitalTotalCost - nextSub - prevSub
			i_next = if i == n then 1 else i + 1
			i_prev = if i == 1 then n else i - 1
			cnext = fromIntegral (costs ! i_next) :: Integer
			cprev = fromIntegral (costs ! i_prev) :: Integer
			nextSub = if Set.member i_next capitals then cnext else 0
			prevSub = if Set.member i_prev capitals then cprev else 0

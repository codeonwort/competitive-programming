import Data.Maybe
import Data.Array
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
--import Debug.Trace

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	[n, m] <- getInts
	cities <- getInts
	towers <- getInts
	let thresholds = if m == 1 then listArray (1,1) [1000000000 + 1] else listArray (1,m-1) (getThresholds towers) :: Array Int Int
	let towers' = listArray (1,m) towers
	print $ solve thresholds towers' cities

getThresholds :: [Int] -> [Int]
getThresholds towers = zipWith (\x y -> (x + y) `div` 2) towers (tail towers)

solve thresholds towers cities = f cities 0 where
	numThresholds = length (elems thresholds)
	f [] soln = soln
	f (x:xs) soln = f xs (max (abs (nearest x - x)) soln)
	nearest x = towers ! (bin x 1 numThresholds)
	bin x i j
		| x > thresholds ! j		= j + 1
		| i >= j					= j
		| thresholds ! mid == x		= mid
		| thresholds ! mid > x		= bin x i mid
		| otherwise					= bin x (mid+1) j
		where mid = (i + j) `div` 2

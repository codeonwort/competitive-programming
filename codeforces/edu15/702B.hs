import Data.Maybe
--import Data.Array
import Data.Bits
import Data.List
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map

-- ID:	702B (Powers of Two)
-- URL:	http://codeforces.com/contest/702/problem/B

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	n <- getInt
	ns <- getInts
	let book = foldl mkBook Map.empty ns :: Map.Map Int Int
	print $ solve book ns

mkBook book x = Map.insertWith (+) x 1 book

solve :: Map.Map Int Int -> [Int] -> Integer
solve book xs = (sum $ map numSoln xs) `div` 2 where
	numSoln x = sum $ map (fromIntegral . calc x) [1..30] :: Integer
	calc x pos
		| goal <= 0 = 0
		| goal `Map.notMember` book = 0
		| goal == x = (book Map.! goal) - 1
		| otherwise = book Map.! goal
		where goal = bit pos - x

{-
-- O(nn) is too slow
let ns' = listArray (1,n) ns :: Array Int Int
print $ length (solve ns' n)
solve :: Array Int Int -> Int -> [Int]
solve ns n = filter pow2 [(ns ! i) + (ns ! j) | i <- [1..n], j <- [i+1..n]]
pow2 :: Int -> Bool
pow2 x = (x .&. (x-1)) == 0
-}

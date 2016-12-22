-- HackerRank.com
-- ID:  Max Min
-- URL: https://www.hackerrank.com/challenges/angry-children

import Control.Monad
import Data.List
import Data.Maybe
import Data.Array
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt

main = do
	n <- getInt
	k <- getInt
	xs <- sort `fmap` replicateM n getInt
	let diffs = zipWith (-) (drop (k-1) xs) xs
	print $ minimum diffs

{-
main = do
	n <- getInt
	k <- getInt
	xs <- replicateM n getInt
	let xs' = listArray (1,n) (sort xs)
	let diffs = map (\i -> (xs' ! (i+k-1)) - (xs' ! i)) [1..n-k+1]
	print $ minimum diffs
-}

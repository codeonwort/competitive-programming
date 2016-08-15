import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.IntSet as Set

-- ID:	Filter Elements
-- URL:	https://www.hackerrank.com/challenges/filter-elements

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	numCases <- getInt
	replicateM_ numCases solve

solve = do
	[n,k] <- getInts
	xs <- getInts
	let set = (Set.fromList . map head . filter (\g -> length g >= k) . group . sort) xs
	case pick xs set of
		[] -> print (-1)
		ys -> putStrLn $ (unwords . map show) ys

pick xs set = f xs set where
	f [] _ = []
	f (x:xs) set
		| Set.member x set = x : f xs (Set.delete x set)
		| otherwise = f xs set

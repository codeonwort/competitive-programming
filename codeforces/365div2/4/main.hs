import Data.Maybe
import Data.List
import Data.Array
import Data.Bits
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map
import Debug.Trace

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

type Book = Map.Map Int [Int]

main = do
	n <- getInt
	xs <- getInts
	m <- getInt
	let xs' = listArray (1,n) xs
	let book = foldl mkBook Map.empty (zip xs [1..n]) :: Book
	let book' = ls2ary book
	replicateM_ m $ do
		[l,r] <- getInts
		print $ solve xs' book' l r

mkBook book (x,i) = Map.insertWith (++) x [i] book
ls2ary book = Map.map (\ls -> listArray (1,length ls) ls) book

solve xs book l r = foldl xor 0 evens where
	xs' = (map head . group . sort) [xs ! i | i <- [l..r]]
	evens = filter even xs'
	even x = numCnt x /= 0 && (numCnt x .&. 1) == 0
	numCnt x = count x r - count x (l-1)
	-- number of x in ary(1,i)
	count x i
		| i <= 0 = 0
		| otherwise = find (book Map.! x) i
	find ary i = f 1 len where
		f lo hi
			| i < ary ! hi = 0
			| lo >= hi = len - hi + 1
			| ary ! mid == i = len - mid + 1
			| ary ! mid > i = f (mid+1) hi
			| otherwise = f lo mid
			where mid = (lo + hi) `div` 2
		len = let (l,r) = bounds ary in r - l + 1 :: Int

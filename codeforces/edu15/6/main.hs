import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	n <- getInt
	shirts <- sortBy compareShirts `fmap` replicateM n getInts
	k <- getInt
	customers <- getInts
	forM_ customers $ \budget -> do
		let soln = buy budget shirts
		putStr (show soln)
		putChar ' '

compareShirts [c1,q1] [c2,q2] = case compare q1 q2 of
	EQ -> compare c1 c2
	LT -> GT
	GT -> LT

buy budget shirts = f budget shirts 0 where
	f _ [] cnt = cnt
	f 0 _ cnt = cnt
	f budget ([cost,quality]:shirts) cnt
		| budget >= cost = f (budget-cost) shirts (cnt+1)
		| otherwise = f budget shirts cnt

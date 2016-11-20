-- Codeforces Round #379 (Div. 2)
-- http://codeforces.com/contest/734

-- ID: 734D (Anton and Chess)
import Control.Monad
import Data.List
import Data.Int
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

type Piece = (String, Int, Int)

getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt

lessX (_,x1,_) (_,x2,_) = compare x1 x2
lessY (_,_,y1) (_,_,y2) = compare y1 y2

main = do
	n <- read `fmap` getLine :: IO Int
	[kingX, kingY] <- (map read . words) `fmap` getLine :: IO [Int]
	blacks <- replicateM n $ do
		[post, x, y] <- BS8.words `fmap` BS.getLine
		return (BS8.unpack post, parseInt x, parseInt y)
	let king = ("K", kingX, kingY)
	let dirs = [(-1,-1,flip lessX), (0,-1,flip lessY), (1,-1,lessX),
				(-1,0,flip lessX), (1,0,lessX),
				(-1,1,flip lessX), (0,1,lessY), (1,1,lessX)]
	let attackers = map fromJust $ filter isJust $ map (choose king blacks) dirs
	if any (checkmate king) attackers
	then putStrLn "YES"
	else putStrLn "NO"

choose king blacks (dx, dy, sorter) = case (sortBy sorter . filter (attack dx dy king)) blacks of
	[] -> Nothing
	xs -> Just (head xs)
attack dx dy (_, kx, ky) (_, x, y)
	| dx == 0 = diffX == 0 && ry >= 1
	| dy == 0 = diffY == 0 && rx >= 1
	| otherwise = rx >= 1 && rx >= 1 && ry == rx
	where
		diffX = x - kx
		diffY = y - ky
		rx = diffX `div` dx
		ry = diffY `div` dy

checkmate (_, kx, ky) (post, x, y)
	| post == "R" = dx == 0 || dy == 0
	| post == "B" = dy /= 0 && (abs (dx `div` dy) == 1)
	| post == "Q" = True
	where
		dx = x - kx
		dy = y - ky


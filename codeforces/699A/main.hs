import Data.Maybe
import Data.Char
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

main = do
	n <- read `fmap` getLine :: IO Int
	dirs <- BS.getLine
	ps <- BS.getLine
	let ns = (map (fst . fromJust . BS8.readInt) . BS8.words) ps :: [Int]
	print (collide ns dirs)

collide :: [Int] -> BS8.ByteString -> Int
collide ns ds = f ns ds (-1) where
	f (n:n2:ns) ds t
		| d == ord 'R' && d2 == ord 'L' = f (n2:ns) ds' (if t == -1 then t' else min t' t)
		| otherwise = f (n2:ns) ds' t
		where
			d = fromIntegral $ BS.head ds
			d2 = fromIntegral $ BS.head (BS.tail ds)
			ds' = BS.tail ds
			t' = (n2 - n) `div` 2
	f _ _ t = t

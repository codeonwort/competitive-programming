import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	[n,q] <- getInts
	events <- replicateM q getInts
	solve events Map.empty [] 0

solve [] _ _ _ = return ()
solve (e:es) book notiQ unread = do
	let [etype, evalue] = e
	if etype == 1
	then do
		let book' = Map.insertWith (+) evalue 1 book
		print (unread + 1)
		solve es book' (evalue:notiQ) (unread + 1)
	else if etype == 2
	then do
		let app = evalue
		let reads = book Map.! app
		let book' = Map.update (\_ -> Just 0) app book
		print (unread - reads)
		solve es book' notiQ (unread - reads)
	else do
		let (toRead,rest) = splitAt evalue (reverse notiQ)
		let (book',numRead) = foldl readQ (book,0) toRead
		print (unread - numRead)
		solve es book' (reverse rest) (unread - numRead)

readQ (book,numRead) app
	| app `Map.notMember` book = (book, numRead)
	| book Map.! app == 0 = (book,numRead)
	| otherwise = (Map.update (\x -> Just (x-1)) app book, numRead+1)

% ----------------------------------------------------------------------- %
%    File_name: deep_learning_cnn.m
%    Programmer: Seungjae Yoo                             
%                                           
%    Last Modified: 2020_01_22                           
%                                                            
 % ----------------------------------------------------------------------- %
 %% Call raw Training data
close all
clear all

% Ask user for input parameters
prompt = {'Data label: ', 'Feature vector length: ', 'Re-referencing: 0 (Non),1 (CAR), 2 (LAP)', 'BFP order'};
dlgtitle = 'Input';
dims = [1 50];
definput = {'a', '3', '1','20'};
answer = inputdlg(prompt,dlgtitle,dims,definput);


% Error detection
if isempty(answer), error("Not enough input parameters."); end

% Input parameters
data_label = string(answer(1,1));   % Calib_ds1 + "data_label"
m = double(string(answer(2,1))); % feature vector will have length (2m)
referencing = double(string(answer(3,1)));
order = double(string(answer(4,1)));

% Load file
FILENAME = strcat('C:\Users\유승재\Desktop\Motor Imagery EEG data\BCICIV_1_mat\BCICIV_calib_ds1',data_label,'.mat');
load(FILENAME);

% Data rescale
cnt= 0.1*double(cnt);
cnt = cnt';

% Exclude electrode (AF3, AF4, O1, O2, PO1, PO2)
cnt_c = cnt(3:55,:);

%% Preprocessing
if referencing ~= 0
    %%% Calculate differential voltage
    for i = 1 : size(cnt_c,1)
        cnt_c(i,:) = cnt_c(i,:) - cnt(29,:);
    end

    
    if referencing == 1 % common average
        Means = (1/size(cnt_c,1))*sum(cnt_c);
        for i = 1 : size(cnt_c,1)
            cnt_c(i,:) = cnt_c(i,:) - Means;
        end
    elseif referencing == 2 % LAP
        %%%
    end
end
%% BPF
%BPF Design
bpFilt = designfilt('bandpassfir','FilterOrder',order, ...
         'CutoffFrequency1',8,'CutoffFrequency2',30, ...
         'SampleRate',100);

% Apply BPF
for i = 1:size(cnt_c,1)
    cnt_c(i,:) = filtfilt(bpFilt, cnt_c(i,:));
end

%% Training set

for i = 1:length(mrk.pos)
    
    % One trial data
    E = cnt_c(:,mrk.pos(1,i):mrk.pos(1,i)+350);   
    
    XTrain(i,1) = {E};    
    YTrain(i,1) = mrk.y(1,i);
    
end
YTrain = categorical(YTrain);

%% True Label

FILENAME = strcat('C:\Users\유승재\Desktop\true_labels\BCICIV_eval_ds1',data_label,'_1000Hz_true_y.mat');
load(FILENAME);
A=[];
B=[];
C=[];
D=[];
%NaN, -1, 0, 1
tmp = 1;
for i=1:length(true_y)-1
    if isnan(true_y(i,1))
        if isnan(true_y(i+1,1))
            continue
        else
            A = [A; [tmp i]];
            tmp = i+1;
        end
    elseif true_y(i,1) ~= true_y(i+1,1)
        if true_y(i,1)== -1
            B = [B; [tmp i]];
        elseif true_y(i,1)== 0
            C = [C; [tmp i]];
        elseif true_y(i,1)== 1
            D = [D; [tmp i]];
        end
        tmp = i+1;
    end
end


%% Call raw Test data
% Load file
FILENAME = strcat('C:\Users\유승재\Desktop\Motor Imagery EEG data\BCICIV_1_mat\BCICIV_eval_ds1',data_label,'.mat');
load(FILENAME);

% Data rescale
cnt= 0.1*double(cnt);
cnt = cnt';

% Exclude electrode (AF3, AF4, O1, O2, PO1, PO2)
cnt_c = cnt(3:55,:);

%% Preprocessing
if referencing ~= 0
    %%% Calculate differential voltage
    for i = 1 : size(cnt_c,1)
        cnt_c(i,:) = cnt_c(i,:) - cnt(29,:);
    end

    
    if referencing == 1 % common average
        Means = (1/size(cnt_c,1))*sum(cnt_c);
        for i = 1 : size(cnt_c,1)
            cnt_c(i,:) = cnt_c(i,:) - Means;
        end
    elseif referencing == 2 % LAP
        %%%
    end
end

%% BPF
%BPF Design
bpFilt = designfilt('bandpassfir','FilterOrder',order, ...
         'CutoffFrequency1',8,'CutoffFrequency2',30, ...
         'SampleRate',100);

% Apply BPF
for i = 1:size(cnt_c,1)
    cnt_c(i,:) = filtfilt(bpFilt, cnt_c(i,:));
end
%% Test set
for j = 1 : length(B)
    tmp1 = round(B(j,1)/10);
    tmp2 = round(B(j,2)/10);
    E = cnt_c(:, tmp1:tmp2);
    
    XTest(j,1) = {E};    
    YTest(j,1) = -1;
 
end

for j = 1 : length(D)
    tmp1 = round(D(j,1)/10);
    tmp2 = round(D(j,2)/10);
    E = cnt_c(:, tmp1:tmp2);
    
    XTest(length(B)+j,1) = {E};    
    YTest(length(B)+j,1) = 1;
 
end
YTest = categorical(YTest);

%%
inputSize = size(cnt_c,1); %%%%%%%%%%%%%%%%%% same with electrode number
numHiddenUnits = 100; %%%%%%%%%%%%%% Change hidden unit number
numClasses = 2;

layers = [ ...
    sequenceInputLayer(inputSize)
    bilstmLayer(numHiddenUnits,'OutputMode','last')
%     dropoutLayer(0.2)
    fullyConnectedLayer(numClasses)
    softmaxLayer
    classificationLayer]; % Can Add: InputWeightsLearnRateFactor, RecurrentWeightsLearnRateFactor, BiasLearnRateFactor, InputWeightsL2Factor

maxEpochs = 300;
% miniBatchSize = 351; %%%%%%%%%%%%%% Change BatchSize -> our data is already chunked

options = trainingOptions('adam', ...
    'ExecutionEnvironment','auto', ...
    'GradientThreshold',1, ...
    'MaxEpochs',maxEpochs, ...
    'SequenceLength','longest', ...
    'Shuffle','never', ...   % "once', 'never', 'every-epoch'
    'ValidationData',{XTest,YTest}, ...
    'ValidationFrequency',10, ...
    'Verbose',0, ...
    'Plots','training-progress');
    
%'LearnRateSchedule','piecewise', ...
    %'LearnRateDropPeriod',10, ...


net = trainNetwork(XTrain,YTrain,layers,options);
%% 
YPred = classify(net,XTest, ...
    'MiniBatchSize',miniBatchSize, ...
    'SequenceLength','longest');

acc = sum(YPred == YTest)./numel(YTest);
 err = immse(str2num(char(YPred(:))), str2num(char(YTest(:))));
 
 disp(sprintf('Score: %f   MSE: %f',acc,err));
